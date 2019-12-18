#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next_bio; TYPE_1__* method; } ;
struct TYPE_5__ {int type; } ;
typedef  TYPE_2__ BIO ;

/* Variables and functions */

BIO *BIO_find_type(BIO *bio, int type)
{
    int mt, mask;

    if (bio == NULL)
        return NULL;
    mask = type & 0xff;
    do {
        if (bio->method != NULL) {
            mt = bio->method->type;

            if (!mask) {
                if (mt & type)
                    return bio;
            } else if (mt == type)
                return bio;
        }
        bio = bio->next_bio;
    } while (bio != NULL);
    return NULL;
}