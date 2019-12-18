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
struct mac {int m_buflen; int /*<<< orphan*/ * m_string; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int MAC_MAX_LABEL_BUF_LEN ; 
 int /*<<< orphan*/  free (struct mac*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,char const*) ; 
 int strlen (char const*) ; 

int
mac_prepare(struct mac **mac, const char *elements)
{

	if (strlen(elements) >= MAC_MAX_LABEL_BUF_LEN)
		return (EINVAL);

	*mac = (struct mac *) malloc(sizeof(**mac));
	if (*mac == NULL)
		return (ENOMEM);

	(*mac)->m_string = malloc(MAC_MAX_LABEL_BUF_LEN);
	if ((*mac)->m_string == NULL) {
		free(*mac);
		*mac = NULL;
		return (ENOMEM);
	}

	strcpy((*mac)->m_string, elements);
	(*mac)->m_buflen = MAC_MAX_LABEL_BUF_LEN;

	return (0);
}