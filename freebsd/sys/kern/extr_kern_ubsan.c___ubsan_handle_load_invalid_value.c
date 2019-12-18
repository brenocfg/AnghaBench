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
struct CInvalidValueData {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct CInvalidValueData*) ; 
 int /*<<< orphan*/  HandleLoadInvalidValue (int,struct CInvalidValueData*,unsigned long) ; 

void
__ubsan_handle_load_invalid_value(struct CInvalidValueData *pData, unsigned long ulValue)
{

	ASSERT(pData);

	HandleLoadInvalidValue(false, pData, ulValue);
}