#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rldram_csr_config_t ;
struct TYPE_8__ {int rld0_mbytes; int rld1_mbytes; int /*<<< orphan*/  rld1_bunks; scalar_t__ rld0_bunks; } ;
typedef  TYPE_1__ llm_descriptor_t ;
typedef  int /*<<< orphan*/  default_llm_desc ;
struct TYPE_9__ {scalar_t__ board_type; } ;
typedef  TYPE_2__ cvmx_sysinfo_t ;

/* Variables and functions */
 scalar_t__ CVMX_BOARD_TYPE_EBH3100 ; 
 scalar_t__ CVMX_BOARD_TYPE_SIM ; 
 int CVMX_LLM_NUM_PORTS ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  cn31xx_dfa_memory_init () ; 
 int /*<<< orphan*/  cvmx_board_type_to_string (scalar_t__) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,...) ; 
 scalar_t__ cvmx_llm_get_default_descriptor (TYPE_1__*) ; 
 TYPE_2__* cvmx_sysinfo_get () ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rld_csr_config_generate (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_rld_cfg (int /*<<< orphan*/ *) ; 

int cvmx_llm_initialize_desc(llm_descriptor_t *llm_desc_ptr)
{
    cvmx_sysinfo_t *sys_ptr;
    sys_ptr = cvmx_sysinfo_get();
    llm_descriptor_t default_llm_desc;

    memset(&default_llm_desc, 0, sizeof(default_llm_desc));
    if (sys_ptr->board_type == CVMX_BOARD_TYPE_SIM)
    {
        cvmx_dprintf("Skipping llm configuration for simulator.\n");
        return 0;
    }

    if (sys_ptr->board_type == CVMX_BOARD_TYPE_EBH3100)
    {
        /* CN31xx DFA memory is DDR based, so it is completely different from the CN38XX DFA memory
        ** config descriptors are not supported yet.*/
        cvmx_dprintf("Warning: preliminary DFA memory configuration\n");
        cn31xx_dfa_memory_init();
        return(256*1024*1024);
    }

    /* If no descriptor passed, generate default descriptor based on board type.
    ** Fail if no default available for given board type
    */
    if (!llm_desc_ptr)
    {
        /* Get default descriptor */
        if (0 > cvmx_llm_get_default_descriptor(&default_llm_desc))
            return -1;

        /* Disable second port depending on CVMX config */
        if (CVMX_LLM_NUM_PORTS == 1)
	  default_llm_desc.rld0_bunks = 0;        // For single port: Force RLD0(P1) to appear EMPTY

        cvmx_dprintf("Using default LLM configuration for board %s (%d)\n", cvmx_board_type_to_string(sys_ptr->board_type),  sys_ptr->board_type);

        llm_desc_ptr = &default_llm_desc;
    }



    rldram_csr_config_t ebt3000_rld_cfg;
    if (!rld_csr_config_generate(llm_desc_ptr, &ebt3000_rld_cfg))
    {
        cvmx_dprintf("Configuring %d llm port(s).\n", !!llm_desc_ptr->rld0_bunks + !!llm_desc_ptr->rld1_bunks);
        write_rld_cfg(&ebt3000_rld_cfg);
    }
    else
    {
        cvmx_dprintf("Error creating rldram configuration\n");
        return(-1);
    }

    /* Compute how much memory is configured
    ** Memory is interleaved, so if one port has more than the other some memory is not usable */

    /* If both ports are enabled, handle the case where one port has more than the other.
    ** This is an unusual and not recommended configuration that exists on the ebt3000 board */
    if (!!llm_desc_ptr->rld0_bunks && !!llm_desc_ptr->rld1_bunks)
        llm_desc_ptr->rld0_mbytes = llm_desc_ptr->rld1_mbytes = MIN(llm_desc_ptr->rld0_mbytes, llm_desc_ptr->rld1_mbytes);

    return(((!!llm_desc_ptr->rld0_bunks) * llm_desc_ptr->rld0_mbytes
          + (!!llm_desc_ptr->rld1_bunks) * llm_desc_ptr->rld1_mbytes) * 1024*1024);
}