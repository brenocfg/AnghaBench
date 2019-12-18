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
struct TYPE_4__ {scalar_t__ params; struct TYPE_4__* value; struct TYPE_4__* name; } ;
typedef  TYPE_1__ MIME_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mime_param_free ; 
 int /*<<< orphan*/  sk_MIME_PARAM_pop_free (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mime_hdr_free(MIME_HEADER *hdr)
{
    if (hdr == NULL)
        return;
    OPENSSL_free(hdr->name);
    OPENSSL_free(hdr->value);
    if (hdr->params)
        sk_MIME_PARAM_pop_free(hdr->params, mime_param_free);
    OPENSSL_free(hdr);
}