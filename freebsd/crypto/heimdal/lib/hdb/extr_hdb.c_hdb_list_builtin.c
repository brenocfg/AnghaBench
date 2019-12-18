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
struct hdb_method {char* prefix; } ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char* malloc (size_t) ; 
 struct hdb_method const* methods ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 
 scalar_t__ strlen (char*) ; 

krb5_error_code
hdb_list_builtin(krb5_context context, char **list)
{
    const struct hdb_method *h;
    size_t len = 0;
    char *buf = NULL;

    for (h = methods; h->prefix != NULL; ++h) {
	if (h->prefix[0] == '\0')
	    continue;
	len += strlen(h->prefix) + 2;
    }

    len += 1;
    buf = malloc(len);
    if (buf == NULL) {
	krb5_set_error_message(context, ENOMEM, "malloc: out of memory");
	return ENOMEM;
    }
    buf[0] = '\0';

    for (h = methods; h->prefix != NULL; ++h) {
	if (h != methods)
	    strlcat(buf, ", ", len);
	strlcat(buf, h->prefix, len);
    }
    *list = buf;
    return 0;
}