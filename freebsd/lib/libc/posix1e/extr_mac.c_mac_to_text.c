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
struct mac {int /*<<< orphan*/  m_string; } ;

/* Variables and functions */
 int ENOMEM ; 
 char* strdup (int /*<<< orphan*/ ) ; 

int
mac_to_text(struct mac *mac, char **text)
{

	*text = strdup(mac->m_string);
	if (*text == NULL)
		return (ENOMEM);
	return (0);
}