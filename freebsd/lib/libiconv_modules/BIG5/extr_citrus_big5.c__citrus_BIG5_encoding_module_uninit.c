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
typedef  int /*<<< orphan*/  _BIG5Exclude ;
struct TYPE_3__ {int /*<<< orphan*/  excludes; } ;
typedef  TYPE_1__ _BIG5EncodingInfo ;

/* Variables and functions */
 int /*<<< orphan*/ * TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
/*ARGSUSED*/
_citrus_BIG5_encoding_module_uninit(_BIG5EncodingInfo *ei)
{
	_BIG5Exclude *exclude;

	while ((exclude = TAILQ_FIRST(&ei->excludes)) != NULL) {
		TAILQ_REMOVE(&ei->excludes, exclude, entry);
		free(exclude);
	}
}