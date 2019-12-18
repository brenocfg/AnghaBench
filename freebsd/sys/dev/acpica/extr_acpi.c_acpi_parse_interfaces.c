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
struct acpi_interface {char** data; int num; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ isspace (char) ; 
 char** malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strdup (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
acpi_parse_interfaces(char *str, struct acpi_interface *iface)
{
	char *p;
	size_t len;
	int i, j;

	p = str;
	while (isspace(*p) || *p == ',')
		p++;
	len = strlen(p);
	if (len == 0)
		return (0);
	p = strdup(p, M_TEMP);
	for (i = 0; i < len; i++)
		if (p[i] == ',')
			p[i] = '\0';
	i = j = 0;
	while (i < len)
		if (isspace(p[i]) || p[i] == '\0')
			i++;
		else {
			i += strlen(p + i) + 1;
			j++;
		}
	if (j == 0) {
		free(p, M_TEMP);
		return (0);
	}
	iface->data = malloc(sizeof(*iface->data) * j, M_TEMP, M_WAITOK);
	iface->num = j;
	i = j = 0;
	while (i < len)
		if (isspace(p[i]) || p[i] == '\0')
			i++;
		else {
			iface->data[j] = p + i;
			i += strlen(p + i) + 1;
			j++;
		}

	return (j);
}