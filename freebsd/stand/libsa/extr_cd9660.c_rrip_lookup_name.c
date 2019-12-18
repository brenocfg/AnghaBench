#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct open_file {int dummy; } ;
struct iso_directory_record {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  length; } ;
struct TYPE_4__ {int* flags; TYPE_1__ h; } ;
typedef  TYPE_2__ ISO_RRIP_ALTNAME ;

/* Variables and functions */
#define  ISO_SUSP_CFLAG_CURRENT 129 
#define  ISO_SUSP_CFLAG_PARENT 128 
 int /*<<< orphan*/  RRIP_NAME ; 
 int /*<<< orphan*/  isonum_711 (int /*<<< orphan*/ ) ; 
 scalar_t__ susp_lookup_record (struct open_file*,int /*<<< orphan*/ ,struct iso_directory_record*,int) ; 

__attribute__((used)) static char *
rrip_lookup_name(struct open_file *f, struct iso_directory_record *dp,
    int lenskip, size_t *len)
{
	ISO_RRIP_ALTNAME *p;

	if (len == NULL)
		return (NULL);

	p = (ISO_RRIP_ALTNAME *)susp_lookup_record(f, RRIP_NAME, dp, lenskip);
	if (p == NULL)
		return (NULL);
	switch (*p->flags) {
	case ISO_SUSP_CFLAG_CURRENT:
		*len = 1;
		return (".");
	case ISO_SUSP_CFLAG_PARENT:
		*len = 2;
		return ("..");
	case 0:
		*len = isonum_711(p->h.length) - 5;
		return ((char *)p + 5);
	default:
		/*
		 * We don't handle hostnames or continued names as they are
		 * too hard, so just bail and use the default name.
		 */
		return (NULL);
	}
}