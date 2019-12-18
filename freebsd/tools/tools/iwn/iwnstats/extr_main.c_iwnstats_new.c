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
struct iwnstats {scalar_t__ s; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 struct iwnstats* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static struct iwnstats *
iwnstats_new(const char *ifname)
{
	struct iwnstats *is;
	char buf[128];

	is = calloc(1, sizeof(struct iwnstats));
	if (is == NULL)
		return (NULL);

	snprintf(buf, sizeof(buf), "/dev/%s", ifname);
	is->s = open(buf, O_RDWR);
	if (is->s < 0)
		err(1, "open");

	return (is);
}