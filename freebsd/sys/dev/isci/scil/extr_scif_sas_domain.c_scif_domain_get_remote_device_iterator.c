#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  remote_device_list; } ;
typedef  int /*<<< orphan*/ **** SCI_ITERATOR_HANDLE_T ;
typedef  scalar_t__ SCI_DOMAIN_HANDLE_T ;
typedef  TYPE_1__ SCIF_SAS_DOMAIN_T ;

/* Variables and functions */
 int /*<<< orphan*/  sci_base_iterator_construct (int /*<<< orphan*/ ****,int /*<<< orphan*/ *) ; 

SCI_ITERATOR_HANDLE_T scif_domain_get_remote_device_iterator(
   SCI_DOMAIN_HANDLE_T   domain,
   void                * iterator_buffer
)
{
   SCI_ITERATOR_HANDLE_T iterator = (SCI_ITERATOR_HANDLE_T *)iterator_buffer;

   sci_base_iterator_construct(
      iterator, &((SCIF_SAS_DOMAIN_T*) domain)->remote_device_list
   );


   return iterator;
}