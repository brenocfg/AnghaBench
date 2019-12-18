#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_char ;
struct TYPE_7__ {int* length; int* version; } ;
struct TYPE_8__ {int* len_id; int* len_des; int* len_src; scalar_t__ ext_data; void** ext_ver; TYPE_1__ h; } ;
struct TYPE_9__ {TYPE_2__ ER; } ;
struct TYPE_10__ {TYPE_3__ su_entry; } ;
struct ISO_SUSP_ATTRIBUTES {TYPE_4__ attr; } ;
struct TYPE_11__ {int /*<<< orphan*/  head; } ;
typedef  TYPE_5__ cd9660node ;

/* Variables and functions */
 int /*<<< orphan*/  SUSP_ENTRY_SUSP_ER ; 
 int /*<<< orphan*/  SUSP_LOC_DOT ; 
 int /*<<< orphan*/  SUSP_TYPE_SUSP ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ISO_SUSP_ATTRIBUTES*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct ISO_SUSP_ATTRIBUTES* cd9660node_susp_create_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,int) ; 
 int /*<<< orphan*/  rr_ll ; 
 scalar_t__ strlen (char const*) ; 

struct ISO_SUSP_ATTRIBUTES*
cd9660_susp_ER(cd9660node *node,
	       u_char ext_version, const char* ext_id, const char* ext_des,
	       const char* ext_src)
{
	int l;
	struct ISO_SUSP_ATTRIBUTES *r;

	r = cd9660node_susp_create_node(SUSP_TYPE_SUSP,
			SUSP_ENTRY_SUSP_ER, "ER", SUSP_LOC_DOT);

	/* Fixed data is 8 bytes */
	r->attr.su_entry.ER.h.length[0] = 8;
	r->attr.su_entry.ER.h.version[0] = 1;

	r->attr.su_entry.ER.len_id[0] = (u_char)strlen(ext_id);
	r->attr.su_entry.ER.len_des[0] = (u_char)strlen(ext_des);
	r->attr.su_entry.ER.len_src[0] = (u_char)strlen(ext_src);

	l = r->attr.su_entry.ER.len_id[0] +
		r->attr.su_entry.ER.len_src[0] +
		r->attr.su_entry.ER.len_des[0];

	/* Everything must fit. */
	assert(l + r->attr.su_entry.ER.h.length[0] <= 254);

	r->attr.su_entry.ER.h.length[0] += (u_char)l;


	r->attr.su_entry.ER.ext_ver[0] = ext_version;
	memcpy(r->attr.su_entry.ER.ext_data, ext_id,
		(int)r->attr.su_entry.ER.len_id[0]);
	l = (int) r->attr.su_entry.ER.len_id[0];
	memcpy(r->attr.su_entry.ER.ext_data + l,ext_des,
		(int)r->attr.su_entry.ER.len_des[0]);

	l += (int)r->attr.su_entry.ER.len_des[0];
	memcpy(r->attr.su_entry.ER.ext_data + l,ext_src,
		(int)r->attr.su_entry.ER.len_src[0]);

	TAILQ_INSERT_TAIL(&node->head, r, rr_ll);
	return r;
}