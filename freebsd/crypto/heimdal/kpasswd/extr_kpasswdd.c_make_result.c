#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_4__ {char* data; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ krb5_data ;

/* Variables and functions */
 int /*<<< orphan*/  asprintf (char**,char*,int,int,char const*) ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  krb5_data_zero (TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
make_result (krb5_data *data,
	     uint16_t result_code,
	     const char *expl)
{
    char *str;
    krb5_data_zero (data);

    data->length = asprintf (&str,
			     "%c%c%s",
			     (result_code >> 8) & 0xFF,
			     result_code & 0xFF,
			     expl);

    if (str == NULL) {
	krb5_warnx (context, "Out of memory generating error reply");
	return 1;
    }
    data->data = str;
    return 0;
}