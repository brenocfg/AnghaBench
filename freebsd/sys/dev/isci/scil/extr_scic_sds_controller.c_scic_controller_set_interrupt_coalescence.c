#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ U8 ;
typedef  scalar_t__ U32 ;
typedef  scalar_t__ U16 ;
struct TYPE_3__ {scalar_t__ interrupt_coalesce_timeout; scalar_t__ interrupt_coalesce_number; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  scalar_t__ SCI_CONTROLLER_HANDLE_T ;
typedef  TYPE_1__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 scalar_t__ INTERRUPT_COALESCE_NUMBER_MAX ; 
 int INTERRUPT_COALESCE_TIMEOUT_BASE_RANGE_LOWER_BOUND_NS ; 
 int INTERRUPT_COALESCE_TIMEOUT_BASE_RANGE_UPPER_BOUND_NS ; 
 scalar_t__ INTERRUPT_COALESCE_TIMEOUT_ENCODE_MAX ; 
 scalar_t__ INTERRUPT_COALESCE_TIMEOUT_ENCODE_MIN ; 
 int INTERRUPT_COALESCE_TIMEOUT_MAX_US ; 
 int /*<<< orphan*/  NUMBER ; 
 int /*<<< orphan*/  SCI_FAILURE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int SMU_ICC_GEN_VAL (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SMU_ICC_WRITE (TYPE_1__*,int) ; 
 int /*<<< orphan*/  TIMER ; 

SCI_STATUS scic_controller_set_interrupt_coalescence(
   SCI_CONTROLLER_HANDLE_T controller,
   U32                     coalesce_number,
   U32                     coalesce_timeout
)
{
   SCIC_SDS_CONTROLLER_T * scic_controller = (SCIC_SDS_CONTROLLER_T *)controller;
   U8 timeout_encode = 0;
   U32 min = 0;
   U32 max = 0;

   //Check if the input parameters fall in the range.
   if (coalesce_number > INTERRUPT_COALESCE_NUMBER_MAX)
      return SCI_FAILURE_INVALID_PARAMETER_VALUE;

   //  Defined encoding for interrupt coalescing timeout:
   //              Value   Min      Max     Units
   //              -----   ---      ---     -----
   //              0       -        -       Disabled
   //              1       13.3     20.0    ns
   //              2       26.7     40.0
   //              3       53.3     80.0
   //              4       106.7    160.0
   //              5       213.3    320.0
   //              6       426.7    640.0
   //              7       853.3    1280.0
   //              8       1.7      2.6     us
   //              9       3.4      5.1
   //              10      6.8      10.2
   //              11      13.7     20.5
   //              12      27.3     41.0
   //              13      54.6     81.9
   //              14      109.2    163.8
   //              15      218.5    327.7
   //              16      436.9    655.4
   //              17      873.8    1310.7
   //              18      1.7      2.6     ms
   //              19      3.5      5.2
   //              20      7.0      10.5
   //              21      14.0     21.0
   //              22      28.0     41.9
   //              23      55.9     83.9
   //              24      111.8    167.8
   //              25      223.7    335.5
   //              26      447.4    671.1
   //              27      894.8    1342.2
   //              28      1.8      2.7     s
   //              Others Undefined

   //Use the table above to decide the encode of interrupt coalescing timeout
   //value for register writing.
   if (coalesce_timeout == 0)
      timeout_encode = 0;
   else
   {
      //make the timeout value in unit of (10 ns).
      coalesce_timeout = coalesce_timeout * 100;
      min = INTERRUPT_COALESCE_TIMEOUT_BASE_RANGE_LOWER_BOUND_NS / 10;
      max = INTERRUPT_COALESCE_TIMEOUT_BASE_RANGE_UPPER_BOUND_NS / 10;

      //get the encode of timeout for register writing.
      for ( timeout_encode = INTERRUPT_COALESCE_TIMEOUT_ENCODE_MIN;
            timeout_encode <= INTERRUPT_COALESCE_TIMEOUT_ENCODE_MAX;
            timeout_encode++ )
      {
         if (min <= coalesce_timeout &&  max > coalesce_timeout)
            break;
         else if (coalesce_timeout >= max && coalesce_timeout < min*2
            && coalesce_timeout <= INTERRUPT_COALESCE_TIMEOUT_MAX_US*100)
         {
            if ( (coalesce_timeout-max) < (2*min - coalesce_timeout) )
               break;
            else
            {
               timeout_encode++;
               break;
            }
         }
         else
         {
            max = max*2;
            min = min*2;
         }
      }

      if ( timeout_encode == INTERRUPT_COALESCE_TIMEOUT_ENCODE_MAX+1 )
         //the value is out of range.
         return SCI_FAILURE_INVALID_PARAMETER_VALUE;
   }

   SMU_ICC_WRITE(
      scic_controller,
      (SMU_ICC_GEN_VAL(NUMBER, coalesce_number)|
       SMU_ICC_GEN_VAL(TIMER, timeout_encode))
   );

   scic_controller->interrupt_coalesce_number = (U16)coalesce_number;
   scic_controller->interrupt_coalesce_timeout = coalesce_timeout/100;

   return SCI_SUCCESS;
}