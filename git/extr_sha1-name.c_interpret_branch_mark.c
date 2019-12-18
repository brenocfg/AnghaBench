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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct repository {int dummy; } ;
typedef  struct branch branch ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 struct branch* branch_get (char*) ; 
 int /*<<< orphan*/  branch_interpret_allowed (char const*,unsigned int) ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ memchr (char const*,char,int) ; 
 int /*<<< orphan*/  set_shortened_ref (struct repository*,struct strbuf*,char const*) ; 
 char* xmemdupz (char const*,int) ; 

__attribute__((used)) static int interpret_branch_mark(struct repository *r,
				 const char *name, int namelen,
				 int at, struct strbuf *buf,
				 int (*get_mark)(const char *, int),
				 const char *(*get_data)(struct branch *,
							 struct strbuf *),
				 unsigned allowed)
{
	int len;
	struct branch *branch;
	struct strbuf err = STRBUF_INIT;
	const char *value;

	len = get_mark(name + at, namelen - at);
	if (!len)
		return -1;

	if (memchr(name, ':', at))
		return -1;

	if (at) {
		char *name_str = xmemdupz(name, at);
		branch = branch_get(name_str);
		free(name_str);
	} else
		branch = branch_get(NULL);

	value = get_data(branch, &err);
	if (!value)
		die("%s", err.buf);

	if (!branch_interpret_allowed(value, allowed))
		return -1;

	set_shortened_ref(r, buf, value);
	return len + at;
}