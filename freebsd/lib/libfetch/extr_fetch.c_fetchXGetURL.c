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
struct url_stat {int dummy; } ;
struct url {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fetchFreeURL (struct url*) ; 
 struct url* fetchParseURL (char const*) ; 
 int /*<<< orphan*/ * fetchXGet (struct url*,struct url_stat*,char const*) ; 

FILE *
fetchXGetURL(const char *URL, struct url_stat *us, const char *flags)
{
	struct url *u;
	FILE *f;

	if ((u = fetchParseURL(URL)) == NULL)
		return (NULL);

	f = fetchXGet(u, us, flags);

	fetchFreeURL(u);
	return (f);
}