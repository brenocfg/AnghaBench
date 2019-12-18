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
struct gctl_req {int dummy; } ;
struct g_provider {int dummy; } ;

/* Variables and functions */
 struct g_provider* g_provider_by_name (char const*) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,char const*) ; 
 char* gctl_get_asciiparam (struct gctl_req*,char const*) ; 

struct g_provider *
gctl_get_provider(struct gctl_req *req, char const *arg)
{
	char const *p;
	struct g_provider *pp;

	p = gctl_get_asciiparam(req, arg);
	if (p == NULL)
		return (NULL);
	pp = g_provider_by_name(p);
	if (pp != NULL)
		return (pp);
	gctl_error(req, "Provider not found: \"%s\"", p);
	return (NULL);
}