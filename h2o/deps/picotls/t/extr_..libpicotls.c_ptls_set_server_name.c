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
struct TYPE_3__ {char* server_name; } ;
typedef  TYPE_1__ ptls_t ;

/* Variables and functions */
 int PTLS_ERROR_NO_MEMORY ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

int ptls_set_server_name(ptls_t *tls, const char *server_name, size_t server_name_len)
{
    char *duped = NULL;

    if (server_name != NULL) {
        if (server_name_len == 0)
            server_name_len = strlen(server_name);
        if ((duped = malloc(server_name_len + 1)) == NULL)
            return PTLS_ERROR_NO_MEMORY;
        memcpy(duped, server_name, server_name_len);
        duped[server_name_len] = '\0';
    }

    free(tls->server_name);
    tls->server_name = duped;

    return 0;
}