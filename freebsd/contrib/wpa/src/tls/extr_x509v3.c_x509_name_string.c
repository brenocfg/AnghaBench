#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct x509_name {size_t num_attr; int /*<<< orphan*/  email; TYPE_1__* attr; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int os_snprintf (char*,int,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ os_snprintf_error (int,int) ; 
 int /*<<< orphan*/  x509_name_attr_str (int /*<<< orphan*/ ) ; 

void x509_name_string(struct x509_name *name, char *buf, size_t len)
{
	char *pos, *end;
	int ret;
	size_t i;

	if (len == 0)
		return;

	pos = buf;
	end = buf + len;

	for (i = 0; i < name->num_attr; i++) {
		ret = os_snprintf(pos, end - pos, "%s=%s, ",
				  x509_name_attr_str(name->attr[i].type),
				  name->attr[i].value);
		if (os_snprintf_error(end - pos, ret))
			goto done;
		pos += ret;
	}

	if (pos > buf + 1 && pos[-1] == ' ' && pos[-2] == ',') {
		pos--;
		*pos = '\0';
		pos--;
		*pos = '\0';
	}

	if (name->email) {
		ret = os_snprintf(pos, end - pos, "/emailAddress=%s",
				  name->email);
		if (os_snprintf_error(end - pos, ret))
			goto done;
		pos += ret;
	}

done:
	if (pos < end)
		*pos = '\0';
	end[-1] = '\0';
}