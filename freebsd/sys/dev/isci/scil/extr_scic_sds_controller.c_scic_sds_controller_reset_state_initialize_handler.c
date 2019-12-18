#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ U32 ;
struct TYPE_28__ {scalar_t__ logical_port_entries; scalar_t__ task_context_entries; scalar_t__ remote_node_entries; int /*<<< orphan*/  port_agent; TYPE_4__* scu_registers; int /*<<< orphan*/ * port_table; int /*<<< orphan*/ * phy_table; int /*<<< orphan*/  timeout_timer; } ;
struct TYPE_25__ {int /*<<< orphan*/ * protocol_engine; int /*<<< orphan*/ * port; } ;
struct TYPE_26__ {int /*<<< orphan*/ * viit; TYPE_2__ ptsg; TYPE_1__* pe; } ;
struct TYPE_27__ {TYPE_3__ peg0; } ;
struct TYPE_24__ {int /*<<< orphan*/  ll; int /*<<< orphan*/  tl; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_CONTROLLER_T ;
typedef  TYPE_5__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 void* MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PCI_RELAXED_ORDERING_ENABLE ; 
 int SCIC_LOG_OBJECT_CONTROLLER ; 
 int SCIC_LOG_OBJECT_INITIALIZATION ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_BASE_CONTROLLER_STATE_INITIALIZED ; 
 int /*<<< orphan*/  SCI_BASE_CONTROLLER_STATE_INITIALIZING ; 
 scalar_t__ SCI_FAILURE ; 
 scalar_t__ SCI_MAX_PHYS ; 
 int /*<<< orphan*/  SCI_MODE_SPEED ; 
 scalar_t__ SCI_SUCCESS ; 
 scalar_t__ SCU_CDMACR_GEN_BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ SCU_CDMACR_READ (TYPE_5__*) ; 
 int /*<<< orphan*/  SCU_CDMACR_WRITE (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  SCU_CONTEXT_RAM_INIT_STALL_TIME ; 
 scalar_t__ SCU_PDMACR_GEN_BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ SCU_PDMACR_READ (TYPE_5__*) ; 
 int /*<<< orphan*/  SCU_PDMACR_WRITE (TYPE_5__*,scalar_t__) ; 
 scalar_t__ SCU_RAM_INIT_COMPLETED ; 
 scalar_t__ SMU_DCC_READ (TYPE_5__*) ; 
 scalar_t__ SMU_SMUCSR_READ (TYPE_5__*) ; 
 int /*<<< orphan*/  SMU_SMUSRCR_WRITE (TYPE_5__*,int) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_cb_stall_execution (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_cb_timer_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_controller_set_mode (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_controller_afe_initialization (TYPE_5__*) ; 
 int /*<<< orphan*/  scic_sds_controller_enable_chipwatch (TYPE_5__*) ; 
 int /*<<< orphan*/  scic_sds_controller_get_base_state_machine (TYPE_5__*) ; 
 int /*<<< orphan*/  scic_sds_controller_initialize_power_control (TYPE_5__*) ; 
 int /*<<< orphan*/  scic_sds_controller_lex_atux_initialization (TYPE_5__*) ; 
 int /*<<< orphan*/  scic_sds_controller_release_resource (TYPE_5__*) ; 
 int /*<<< orphan*/  scic_sds_controller_reset_hardware (TYPE_5__*) ; 
 int /*<<< orphan*/  scic_sds_controller_timeout_handler ; 
 scalar_t__ scic_sds_phy_initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ scic_sds_port_configuration_agent_initialize (TYPE_5__*,int /*<<< orphan*/ *) ; 
 scalar_t__ scic_sds_port_initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sgpio_hardware_initialize (TYPE_5__*) ; 
 int /*<<< orphan*/  scu_register_write (TYPE_5__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ smu_dcc_get_max_ports (scalar_t__) ; 
 scalar_t__ smu_dcc_get_max_remote_node_context (scalar_t__) ; 
 scalar_t__ smu_dcc_get_max_task_context (scalar_t__) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_controller_reset_state_initialize_handler(
   SCI_BASE_CONTROLLER_T *controller
)
{
   U32 index;
   SCI_STATUS result = SCI_SUCCESS;
   SCIC_SDS_CONTROLLER_T *this_controller;

   this_controller = (SCIC_SDS_CONTROLLER_T *)controller;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(controller),
      SCIC_LOG_OBJECT_CONTROLLER | SCIC_LOG_OBJECT_INITIALIZATION,
      "scic_sds_controller_reset_state_initialize_handler(0x%x) enter\n",
      controller
   ));

   sci_base_state_machine_change_state(
      scic_sds_controller_get_base_state_machine(this_controller),
      SCI_BASE_CONTROLLER_STATE_INITIALIZING
   );

   this_controller->timeout_timer = scic_cb_timer_create(
      controller,
      scic_sds_controller_timeout_handler,
      controller
   );

   scic_sds_controller_initialize_power_control(this_controller);

   /// todo: This should really be done in the reset state enter but
   ///       the controller has not yet been initialized before getting
   ///       to the reset enter state so the PCI BAR is not yet assigned
   scic_sds_controller_reset_hardware(this_controller);

#if defined(ARLINGTON_BUILD)
   scic_sds_controller_lex_atux_initialization(this_controller);
#elif    defined(PLEASANT_RIDGE_BUILD) \
      || defined(PBG_HBA_A0_BUILD) \
      || defined(PBG_HBA_A2_BUILD)
   scic_sds_controller_afe_initialization(this_controller);
#elif defined(PBG_HBA_BETA_BUILD) || defined(PBG_BUILD)
   // There is nothing to do here for B0 since we do not have to
   // program the AFE registers.
   /// @todo The AFE settings are supposed to be correct for the B0 but
   ///       presently they seem to be wrong.
   scic_sds_controller_afe_initialization(this_controller);
#else  // !defined(ARLINGTON_BUILD) && !defined(PLEASANT_RIDGE_BUILD)
   // What other systems do we want to add here?
#endif // !defined(ARLINGTON_BUILD) && !defined(PLEASANT_RIDGE_BUILD)

   if (SCI_SUCCESS == result)
   {
      U32 status;
      U32 terminate_loop;

      // Take the hardware out of reset
      SMU_SMUSRCR_WRITE(this_controller, 0x00000000);

      /// @todo Provide meaningfull error code for hardware failure
      //result = SCI_FAILURE_CONTROLLER_HARDWARE;
      result = SCI_FAILURE;
      terminate_loop = 100;

      while (terminate_loop-- && (result != SCI_SUCCESS))
      {
         // Loop until the hardware reports success
         scic_cb_stall_execution(SCU_CONTEXT_RAM_INIT_STALL_TIME);
         status = SMU_SMUCSR_READ(this_controller);

         if ((status & SCU_RAM_INIT_COMPLETED) == SCU_RAM_INIT_COMPLETED)
         {
            result = SCI_SUCCESS;
         }
      }
   }

#ifdef ARLINGTON_BUILD
   scic_sds_controller_enable_chipwatch(this_controller);
#endif

   if (result == SCI_SUCCESS)
   {
      U32 max_supported_ports;
      U32 max_supported_devices;
      U32 max_supported_io_requests;
      U32 device_context_capacity;

      // Determine what are the actaul device capacities that the
      // hardware will support
      device_context_capacity = SMU_DCC_READ(this_controller);

      max_supported_ports =
         smu_dcc_get_max_ports(device_context_capacity);
      max_supported_devices =
         smu_dcc_get_max_remote_node_context(device_context_capacity);
      max_supported_io_requests =
         smu_dcc_get_max_task_context(device_context_capacity);

      // Make all PEs that are unassigned match up with the logical ports
      for (index = 0; index < max_supported_ports; index++)
      {
         scu_register_write(
            this_controller,
            this_controller->scu_registers->peg0.ptsg.protocol_engine[index],
            index
         );
      }

      // Now that we have the correct hardware reported minimum values
      // build the MDL for the controller.  Default to a performance
      // configuration.
      scic_controller_set_mode(this_controller, SCI_MODE_SPEED);

      // Record the smaller of the two capacity values
      this_controller->logical_port_entries =
         MIN(max_supported_ports, this_controller->logical_port_entries);

      this_controller->task_context_entries =
         MIN(max_supported_io_requests, this_controller->task_context_entries);

      this_controller->remote_node_entries =
         MIN(max_supported_devices, this_controller->remote_node_entries);
   }

   // Initialize hardware PCI Relaxed ordering in DMA engines
   if (result == SCI_SUCCESS)
   {
      U32 dma_configuration;

      // Configure the payload DMA
      dma_configuration = SCU_PDMACR_READ(this_controller);
      dma_configuration |= SCU_PDMACR_GEN_BIT(PCI_RELAXED_ORDERING_ENABLE);
      SCU_PDMACR_WRITE(this_controller, dma_configuration);

      // Configure the control DMA
      dma_configuration = SCU_CDMACR_READ(this_controller);
      dma_configuration |= SCU_CDMACR_GEN_BIT(PCI_RELAXED_ORDERING_ENABLE);
      SCU_CDMACR_WRITE(this_controller, dma_configuration);
   }

   // Initialize the PHYs before the PORTs because the PHY registers
   // are accessed during the port initialization.
   if (result == SCI_SUCCESS)
   {
      // Initialize the phys
      for (index = 0;
           (result == SCI_SUCCESS) && (index < SCI_MAX_PHYS);
           index++)
      {
         result = scic_sds_phy_initialize(
            &this_controller->phy_table[index],
            &this_controller->scu_registers->peg0.pe[index].tl,
            &this_controller->scu_registers->peg0.pe[index].ll
         );
      }
   }

   //Initialize the SGPIO Unit for HARDWARE controlled SGPIO
   if(result == SCI_SUCCESS)
   {
      scic_sgpio_hardware_initialize(this_controller);
   }

   if (result == SCI_SUCCESS)
   {
      // Initialize the logical ports
      for (index = 0;
              (index < this_controller->logical_port_entries)
           && (result == SCI_SUCCESS);
           index++)
      {
         result = scic_sds_port_initialize(
            &this_controller->port_table[index],
            &this_controller->scu_registers->peg0.ptsg.port[index],
            &this_controller->scu_registers->peg0.ptsg.protocol_engine,
            &this_controller->scu_registers->peg0.viit[index]
         );
      }
   }

   if (SCI_SUCCESS == result)
   {
      result = scic_sds_port_configuration_agent_initialize(
                  this_controller,
                  &this_controller->port_agent
               );
   }

   // Advance the controller state machine
   if (result == SCI_SUCCESS)
   {
      sci_base_state_machine_change_state(
         scic_sds_controller_get_base_state_machine(this_controller),
         SCI_BASE_CONTROLLER_STATE_INITIALIZED
      );
   }
   else
   {
      //stay in the same state and release the resource
      scic_sds_controller_release_resource(this_controller);

      SCIC_LOG_TRACE((
         sci_base_object_get_logger(controller),
         SCIC_LOG_OBJECT_CONTROLLER | SCIC_LOG_OBJECT_INITIALIZATION,
         "Invalid Port Configuration from scic_sds_controller_reset_state_initialize_handler(0x%x) \n",
         controller
      ));

   }

   return result;
}