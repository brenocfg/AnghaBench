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
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dh_groups_get (int) ; 
 struct wpabuf* dh_init (int /*<<< orphan*/ ,struct wpabuf**) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 

void * dh5_init(struct wpabuf **priv, struct wpabuf **publ)
{
	wpabuf_free(*publ);
	*publ = dh_init(dh_groups_get(5), priv);
	if (*publ == NULL)
		return NULL;
	return (void *) 1;
}