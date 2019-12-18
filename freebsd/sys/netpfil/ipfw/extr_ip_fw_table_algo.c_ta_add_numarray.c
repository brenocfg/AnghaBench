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
typedef  int uint32_t ;
struct tentry_info {int value; int flags; } ;
struct table_info {scalar_t__ data; } ;
struct TYPE_2__ {int value; int /*<<< orphan*/  number; } ;
struct ta_buf_numarray {TYPE_1__ na; } ;
struct numarray_cfg {scalar_t__ used; int /*<<< orphan*/  main_ptr; } ;
struct numarray {int value; } ;

/* Variables and functions */
 int EEXIST ; 
 int EFBIG ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int TEI_FLAGS_DONTADD ; 
 int TEI_FLAGS_UPDATE ; 
 int TEI_FLAGS_UPDATED ; 
 int badd (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compare_numarray ; 
 struct numarray* numarray_find (struct table_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ta_add_numarray(void *ta_state, struct table_info *ti, struct tentry_info *tei,
    void *ta_buf, uint32_t *pnum)
{
	struct numarray_cfg *cfg;
	struct ta_buf_numarray *tb;
	struct numarray *ri;
	int res;
	uint32_t value;

	tb = (struct ta_buf_numarray *)ta_buf;
	cfg = (struct numarray_cfg *)ta_state;

	/* Read current value from @tei */
	tb->na.value = tei->value;

	ri = numarray_find(ti, &tb->na.number);
	
	if (ri != NULL) {
		if ((tei->flags & TEI_FLAGS_UPDATE) == 0)
			return (EEXIST);

		/* Exchange values between ri and @tei */
		value = ri->value;
		ri->value = tei->value;
		tei->value = value;
		/* Indicate that update has happened instead of addition */
		tei->flags |= TEI_FLAGS_UPDATED;
		*pnum = 0;
		return (0);
	}

	if ((tei->flags & TEI_FLAGS_DONTADD) != 0)
		return (EFBIG);

	res = badd(&tb->na.number, &tb->na, cfg->main_ptr, cfg->used,
	    sizeof(struct numarray), compare_numarray);

	KASSERT(res == 1, ("number %d already exists", tb->na.number));
	cfg->used++;
	ti->data = cfg->used;
	*pnum = 1;

	return (0);
}