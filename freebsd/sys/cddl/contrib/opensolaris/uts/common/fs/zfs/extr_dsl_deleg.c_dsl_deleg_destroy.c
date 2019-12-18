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
typedef  int /*<<< orphan*/  zap_cursor_t ;
struct TYPE_3__ {int za_integer_length; int za_num_integers; int /*<<< orphan*/  za_first_integer; } ;
typedef  TYPE_1__ zap_attribute_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  zap_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ zap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
dsl_deleg_destroy(objset_t *mos, uint64_t zapobj, dmu_tx_t *tx)
{
	zap_cursor_t zc;
	zap_attribute_t za;

	if (zapobj == 0)
		return (0);

	for (zap_cursor_init(&zc, mos, zapobj);
	    zap_cursor_retrieve(&zc, &za) == 0;
	    zap_cursor_advance(&zc)) {
		ASSERT(za.za_integer_length == 8 && za.za_num_integers == 1);
		VERIFY(0 == zap_destroy(mos, za.za_first_integer, tx));
	}
	zap_cursor_fini(&zc);
	VERIFY(0 == zap_destroy(mos, zapobj, tx));
	return (0);
}