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
struct pf_anchor {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 struct pf_anchor* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pf_anchor*) ; 
 int /*<<< orphan*/  V_pf_anchors ; 
 int /*<<< orphan*/  pf_anchor_global ; 
 int /*<<< orphan*/  rs_free (struct pf_anchor*) ; 
 scalar_t__ rs_malloc (int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static struct pf_anchor *
pf_find_anchor(const char *path)
{
	struct pf_anchor	*key, *found;

	key = (struct pf_anchor *)rs_malloc(sizeof(*key));
	if (key == NULL)
		return (NULL);
	strlcpy(key->path, path, sizeof(key->path));
	found = RB_FIND(pf_anchor_global, &V_pf_anchors, key);
	rs_free(key);
	return (found);
}