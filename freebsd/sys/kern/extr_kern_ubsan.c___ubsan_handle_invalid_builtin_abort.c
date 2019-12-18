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
struct CInvalidBuiltinData {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct CInvalidBuiltinData*) ; 
 int /*<<< orphan*/  HandleInvalidBuiltin (int,struct CInvalidBuiltinData*) ; 

void
__ubsan_handle_invalid_builtin_abort(struct CInvalidBuiltinData *pData)
{

	ASSERT(pData);

	HandleInvalidBuiltin(true, pData);
}