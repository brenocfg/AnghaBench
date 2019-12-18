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
struct parse_arg {scalar_t__ norm; int /*<<< orphan*/  dst; } ;
struct _region {int dummy; } ;
struct _lookup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_PIVOT ; 
 int /*<<< orphan*/  _LOOKUP_CASE_IGNORE ; 
 int /*<<< orphan*/  _lookup_seq_close (struct _lookup*) ; 
 int _lookup_seq_lookup (struct _lookup*,int /*<<< orphan*/ ,struct _region*) ; 
 int _lookup_seq_next (struct _lookup*,int /*<<< orphan*/ *,struct _region*) ; 
 int _lookup_seq_open (struct _lookup**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int parse_line (struct parse_arg*,struct _region*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
find_dst(struct parse_arg *pasrc, const char *dst)
{
	struct _lookup *cl;
	struct parse_arg padst;
	struct _region data;
	int ret;

	ret = _lookup_seq_open(&cl, CS_PIVOT, _LOOKUP_CASE_IGNORE);
	if (ret)
		return (ret);

	ret = _lookup_seq_lookup(cl, pasrc->dst, &data);
	while (ret == 0) {
		ret = parse_line(&padst, &data);
		if (ret)
			break;
		if (strcmp(dst, padst.dst) == 0) {
			pasrc->norm += padst.norm;
			break;
		}
		ret = _lookup_seq_next(cl, NULL, &data);
	}
	_lookup_seq_close(cl);

	return (ret);
}