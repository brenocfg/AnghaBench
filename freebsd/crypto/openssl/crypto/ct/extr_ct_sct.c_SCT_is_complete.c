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
struct TYPE_4__ {int version; int /*<<< orphan*/ * sct; int /*<<< orphan*/ * log_id; } ;
typedef  TYPE_1__ SCT ;

/* Variables and functions */
#define  SCT_VERSION_NOT_SET 129 
#define  SCT_VERSION_V1 128 
 int /*<<< orphan*/  SCT_signature_is_complete (TYPE_1__ const*) ; 

int SCT_is_complete(const SCT *sct)
{
    switch (sct->version) {
    case SCT_VERSION_NOT_SET:
        return 0;
    case SCT_VERSION_V1:
        return sct->log_id != NULL && SCT_signature_is_complete(sct);
    default:
        return sct->sct != NULL; /* Just need cached encoding */
    }
}