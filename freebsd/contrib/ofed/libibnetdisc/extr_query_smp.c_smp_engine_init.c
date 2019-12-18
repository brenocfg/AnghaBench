#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ umad_fd; int /*<<< orphan*/ * cfg; int /*<<< orphan*/  smps_on_wire; void* user_data; void* smi_dir_agent; void* smi_agent; } ;
typedef  TYPE_1__ smp_engine_t ;
typedef  int /*<<< orphan*/  ibnd_config_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IBND_ERROR (char*,...) ; 
 int /*<<< orphan*/  IB_SMI_CLASS ; 
 int /*<<< orphan*/  IB_SMI_DIRECT_CLASS ; 
 int /*<<< orphan*/  cl_qmap_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  umad_close_port (scalar_t__) ; 
 scalar_t__ umad_init () ; 
 scalar_t__ umad_open_port (char*,int) ; 
 void* umad_register (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int smp_engine_init(smp_engine_t * engine, char * ca_name, int ca_port,
		    void *user_data, ibnd_config_t *cfg)
{
	memset(engine, 0, sizeof(*engine));

	if (umad_init() < 0) {
		IBND_ERROR("umad_init failed\n");
		return -EIO;
	}

	engine->umad_fd = umad_open_port(ca_name, ca_port);
	if (engine->umad_fd < 0) {
		IBND_ERROR("can't open UMAD port (%s:%d)\n", ca_name, ca_port);
		return -EIO;
	}

	if ((engine->smi_agent = umad_register(engine->umad_fd,
	     IB_SMI_CLASS, 1, 0, 0)) < 0) {
		IBND_ERROR("Failed to register SMI agent on (%s:%d)\n",
			   ca_name, ca_port);
		goto eio_close;
	}

	if ((engine->smi_dir_agent = umad_register(engine->umad_fd,
	     IB_SMI_DIRECT_CLASS, 1, 0, 0)) < 0) {
		IBND_ERROR("Failed to register SMI_DIRECT agent on (%s:%d)\n",
			   ca_name, ca_port);
		goto eio_close;
	}

	engine->user_data = user_data;
	cl_qmap_init(&engine->smps_on_wire);
	engine->cfg = cfg;
	return (0);

eio_close:
	umad_close_port(engine->umad_fd);
	return (-EIO);
}