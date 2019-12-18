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
struct TYPE_3__ {char* negotiated_protocol; } ;
typedef  TYPE_1__ ptls_t ;

/* Variables and functions */
 int PTLS_ERROR_NO_MEMORY ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

int ptls_set_negotiated_protocol(ptls_t *tls, const char *protocol, size_t protocol_len)
{
    char *duped = NULL;

    if (protocol != NULL) {
        if (protocol_len == 0)
            protocol_len = strlen(protocol);
        if ((duped = malloc(protocol_len + 1)) == NULL)
            return PTLS_ERROR_NO_MEMORY;
        memcpy(duped, protocol, protocol_len);
        duped[protocol_len] = '\0';
    }

    free(tls->negotiated_protocol);
    tls->negotiated_protocol = duped;

    return 0;
}