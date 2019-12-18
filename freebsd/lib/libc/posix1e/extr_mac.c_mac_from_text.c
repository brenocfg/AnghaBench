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
struct mac {int /*<<< orphan*/ * m_string; scalar_t__ m_buflen; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  free (struct mac*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 

int
mac_from_text(struct mac **mac, const char *text)
{

	*mac = (struct mac *) malloc(sizeof(**mac));
	if (*mac == NULL)
		return (ENOMEM);

	(*mac)->m_string = strdup(text);
	if ((*mac)->m_string == NULL) {
		free(*mac);
		*mac = NULL;
		return (ENOMEM);
	}

	(*mac)->m_buflen = strlen((*mac)->m_string)+1;

	return (0);
}