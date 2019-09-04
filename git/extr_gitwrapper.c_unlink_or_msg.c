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
struct strbuf {int dummy; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  assert (struct strbuf*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int unlink (char const*) ; 

int unlink_or_msg(const char *file, struct strbuf *err)
{
	int rc = unlink(file);

	assert(err);

	if (!rc || errno == ENOENT)
		return 0;

	strbuf_addf(err, "unable to unlink '%s': %s",
		    file, strerror(errno));
	return -1;
}