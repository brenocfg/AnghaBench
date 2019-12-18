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
struct maplink {int /*<<< orphan*/  ml_mapper; } ;
struct _citrus_mapper_serial {int /*<<< orphan*/  sr_mappers; } ;

/* Variables and functions */
 struct maplink* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mapper_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct maplink*) ; 
 int /*<<< orphan*/  ml_entry ; 

__attribute__((used)) static void
uninit(struct _citrus_mapper_serial *sr)
{
	struct maplink *ml;

	while ((ml = STAILQ_FIRST(&sr->sr_mappers)) != NULL) {
		STAILQ_REMOVE_HEAD(&sr->sr_mappers, ml_entry);
		_mapper_close(ml->ml_mapper);
		free(ml);
	}
}