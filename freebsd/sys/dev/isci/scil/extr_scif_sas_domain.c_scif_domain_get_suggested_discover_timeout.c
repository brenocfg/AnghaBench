#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  SCI_DOMAIN_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_DOMAIN_DISCOVER_TIMEOUT ; 

U32 scif_domain_get_suggested_discover_timeout(
   SCI_DOMAIN_HANDLE_T   domain
)
{
   U32 suggested_timeout = SCIF_DOMAIN_DISCOVER_TIMEOUT; //milli-seconds
   return suggested_timeout;
}