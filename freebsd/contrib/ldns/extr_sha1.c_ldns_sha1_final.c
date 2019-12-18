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
struct TYPE_4__ {int count; int* state; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ ldns_sha1_ctx ;

/* Variables and functions */
 unsigned int LDNS_SHA1_DIGEST_LENGTH ; 
 int /*<<< orphan*/  ldns_sha1_transform (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_sha1_update (TYPE_1__*,unsigned char*,int) ; 

void
ldns_sha1_final(unsigned char digest[LDNS_SHA1_DIGEST_LENGTH], ldns_sha1_ctx *context)
{
    unsigned int i;
    unsigned char finalcount[8];

    for (i = 0; i < 8; i++) {
        finalcount[i] = (unsigned char)((context->count >>
            ((7 - (i & 7)) * 8)) & 255);  /* Endian independent */
    }
    ldns_sha1_update(context, (unsigned char *)"\200", 1);
    while ((context->count & 504) != 448) {
        ldns_sha1_update(context, (unsigned char *)"\0", 1);
    }
    ldns_sha1_update(context, finalcount, 8);  /* Should cause a SHA1Transform() */

    if (digest != NULL)
        for (i = 0; i < LDNS_SHA1_DIGEST_LENGTH; i++) {
            digest[i] = (unsigned char)((context->state[i >> 2] >>
                ((3 - (i & 3)) * 8)) & 255);
      }
#ifdef SHA1HANDSOFF  /* make SHA1Transform overwrite its own static vars */
    ldns_sha1_transform(context->state, context->buffer);
#endif
}