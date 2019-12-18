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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct val_anchors {int dummy; } ;
struct trust_anchor {int dummy; } ;

/* Variables and functions */
 struct trust_anchor* autr_tp_create (struct val_anchors*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_int (char*,int*) ; 
 int /*<<< orphan*/ * sldns_str2wire_dname (char*,size_t*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static struct trust_anchor*
parse_id(struct val_anchors* anchors, char* line)
{
	struct trust_anchor *tp;
	int r;
	uint16_t dclass;
	uint8_t* dname;
	size_t dname_len;
	/* read the owner name */
	char* next = strchr(line, ' ');
	if(!next)
		return NULL;
	next[0] = 0;
	dname = sldns_str2wire_dname(line, &dname_len);
	if(!dname)
		return NULL;

	/* read the class */
	dclass = parse_int(next+1, &r);
	if(r == -1) {
		free(dname);
		return NULL;
	}

	/* find the trust point */
	tp = autr_tp_create(anchors, dname, dname_len, dclass);
	free(dname);
	return tp;
}