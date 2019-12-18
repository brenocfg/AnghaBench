#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/  krb5_error_code ;
struct TYPE_3__ {char* data; size_t length; } ;
typedef  TYPE_1__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  append_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hex_encode (char*,size_t,char**) ; 
 int /*<<< orphan*/  isalnum (unsigned char) ; 

__attribute__((used)) static krb5_error_code
append_hex(krb5_context context, krb5_storage *sp, krb5_data *data)
{
    int printable = 1;
    size_t i;
    char *p;

    p = data->data;
    for(i = 0; i < data->length; i++)
	if(!isalnum((unsigned char)p[i]) && p[i] != '.'){
	    printable = 0;
	    break;
	}
    if(printable)
	return append_string(context, sp, "\"%.*s\"",
			     data->length, data->data);
    hex_encode(data->data, data->length, &p);
    append_string(context, sp, "%s", p);
    free(p);
    return 0;
}