#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int devlist_lockcreated; int /*<<< orphan*/  scan_lock; int /*<<< orphan*/  devlist_lock; int /*<<< orphan*/ *** device_list; scalar_t__ prev_heartbeat_count; int /*<<< orphan*/  num_intrs; int /*<<< orphan*/  prev_num_intrs; int /*<<< orphan*/  devlist_lock_name; } ;
typedef  TYPE_1__ pqisrc_softstate_t ;

/* Variables and functions */
 scalar_t__ CTRLR_HEARTBEAT_CNT (TYPE_1__*) ; 
 int /*<<< orphan*/  DBG_ERR (char*,...) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  LOCKNAME_SIZE ; 
 int /*<<< orphan*/  OS_ATOMIC64_SET (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OS_FW_HEARTBEAT_TIMER_INTERVAL ; 
 int PQI_MAX_DEVICES ; 
 int PQI_MAX_MULTILUN ; 
 scalar_t__ PQI_NEW_HEARTBEAT_MECHANISM (TYPE_1__*) ; 
 int PQI_STATUS_SUCCESS ; 
 int /*<<< orphan*/  check_struct_sizes () ; 
 int /*<<< orphan*/  num_intrs ; 
 int os_create_semaphore (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_destroy_intr (TYPE_1__*) ; 
 int /*<<< orphan*/  os_destroy_semaphore (int /*<<< orphan*/ *) ; 
 int os_init_spinlock (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int os_setup_intr (TYPE_1__*) ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_uninit_spinlock (int /*<<< orphan*/ *) ; 
 int pqisrc_get_ctrl_fw_version (TYPE_1__*) ; 
 int /*<<< orphan*/  pqisrc_init_targetid_pool (TYPE_1__*) ; 
 int pqisrc_pqi_init (TYPE_1__*) ; 
 int /*<<< orphan*/  pqisrc_pqi_uninit (TYPE_1__*) ; 
 int pqisrc_process_config_table (TYPE_1__*) ; 
 int pqisrc_report_event_config (TYPE_1__*) ; 
 int pqisrc_set_event_config (TYPE_1__*) ; 
 int pqisrc_sis_init (TYPE_1__*) ; 
 int /*<<< orphan*/  pqisrc_sis_uninit (TYPE_1__*) ; 
 int pqisrc_write_driver_version_to_host_wellness (TYPE_1__*) ; 

int pqisrc_init(pqisrc_softstate_t *softs)
{
	int ret = 0;
	int i = 0, j = 0;

	DBG_FUNC("IN\n");
    
	check_struct_sizes();
    
	/* Init the Sync interface */
	ret = pqisrc_sis_init(softs);
	if (ret) {
		DBG_ERR("SIS Init failed with error %d\n", ret);
		goto err_out;
	}

	ret = os_create_semaphore("scan_lock", 1, &softs->scan_lock);
	if(ret != PQI_STATUS_SUCCESS){
		DBG_ERR(" Failed to initialize scan lock\n");
		goto err_scan_lock;
	}

	/* Init the PQI interface */
	ret = pqisrc_pqi_init(softs);
	if (ret) {
		DBG_ERR("PQI Init failed with error %d\n", ret);
		goto err_pqi;
	}

	/* Setup interrupt */
	ret = os_setup_intr(softs);
	if (ret) {
		DBG_ERR("Interrupt setup failed with error %d\n", ret);
		goto err_intr;
	}

	/* Report event configuration */
        ret = pqisrc_report_event_config(softs);
        if(ret){
                DBG_ERR(" Failed to configure Report events\n");
		goto err_event;
	}
	 
	/* Set event configuration*/
        ret = pqisrc_set_event_config(softs);
        if(ret){
                DBG_ERR(" Failed to configure Set events\n");
                goto err_event;
        }

	/* Check for For PQI spanning */
	ret = pqisrc_get_ctrl_fw_version(softs);
        if(ret){
                DBG_ERR(" Failed to get ctrl fw version\n");
		goto err_fw_version;
        }

	/* update driver version in to FW */
	ret = pqisrc_write_driver_version_to_host_wellness(softs);
	if (ret) {
		DBG_ERR(" Failed to update driver version in to FW");
		goto err_host_wellness;
	}

    
	os_strlcpy(softs->devlist_lock_name, "devlist_lock", LOCKNAME_SIZE);
	ret = os_init_spinlock(softs, &softs->devlist_lock, softs->devlist_lock_name);
	if(ret){
		DBG_ERR(" Failed to initialize devlist_lock\n");
		softs->devlist_lockcreated=false;
		goto err_lock;
	}
	softs->devlist_lockcreated = true;
	
	OS_ATOMIC64_SET(softs, num_intrs, 0);
	softs->prev_num_intrs = softs->num_intrs;


	/* Get the PQI configuration table to read heart-beat counter*/
	if (PQI_NEW_HEARTBEAT_MECHANISM(softs)) {
		ret = pqisrc_process_config_table(softs);
		if (ret) {
			DBG_ERR("Failed to process PQI configuration table %d\n", ret);
			goto err_config_tab;
		}
	}

	if (PQI_NEW_HEARTBEAT_MECHANISM(softs))
		softs->prev_heartbeat_count = CTRLR_HEARTBEAT_CNT(softs) - OS_FW_HEARTBEAT_TIMER_INTERVAL;
	
	/* Init device list */
	for(i = 0; i < PQI_MAX_DEVICES; i++)
		for(j = 0; j < PQI_MAX_MULTILUN; j++)
			softs->device_list[i][j] = NULL;

	pqisrc_init_targetid_pool(softs);

	DBG_FUNC("OUT\n");
	return ret;

err_config_tab:
	if(softs->devlist_lockcreated==true){    
		os_uninit_spinlock(&softs->devlist_lock);
		softs->devlist_lockcreated = false;
	}	
err_lock:
err_fw_version:
err_event:
err_host_wellness:
	os_destroy_intr(softs);
err_intr:
	pqisrc_pqi_uninit(softs);
err_pqi:
	os_destroy_semaphore(&softs->scan_lock);
err_scan_lock:
	pqisrc_sis_uninit(softs);
err_out:
	DBG_FUNC("OUT failed\n");
	return ret;
}