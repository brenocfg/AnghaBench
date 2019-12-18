#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ id; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ isc_logcategory_t ;
struct TYPE_8__ {int /*<<< orphan*/  category_count; TYPE_1__* categories; } ;
typedef  TYPE_2__ isc_log_t ;

/* Variables and functions */
 int /*<<< orphan*/  DE_CONST (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 scalar_t__ UINT_MAX ; 
 int VALID_CONTEXT (TYPE_2__*) ; 

void
isc_log_registercategories(isc_log_t *lctx, isc_logcategory_t categories[]) {
	isc_logcategory_t *catp;

	REQUIRE(VALID_CONTEXT(lctx));
	REQUIRE(categories != NULL && categories[0].name != NULL);

	/*
	 * XXXDCL This somewhat sleazy situation of using the last pointer
	 * in one category array to point to the next array exists because
	 * this registration function returns void and I didn't want to have
	 * change everything that used it by making it return an isc_result_t.
	 * It would need to do that if it had to allocate memory to store
	 * pointers to each array passed in.
	 */
	if (lctx->categories == NULL)
		lctx->categories = categories;

	else {
		/*
		 * Adjust the last (NULL) pointer of the already registered
		 * categories to point to the incoming array.
		 */
		for (catp = lctx->categories; catp->name != NULL; )
			if (catp->id == UINT_MAX)
				/*
				 * The name pointer points to the next array.
				 * Ick.
				 */
				DE_CONST(catp->name, catp);
			else
				catp++;

		catp->name = (void *)categories;
		catp->id = UINT_MAX;
	}

	/*
	 * Update the id number of the category with its new global id.
	 */
	for (catp = categories; catp->name != NULL; catp++)
		catp->id = lctx->category_count++;
}