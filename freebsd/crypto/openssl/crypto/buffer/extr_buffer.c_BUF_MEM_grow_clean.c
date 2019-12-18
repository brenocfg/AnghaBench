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
struct TYPE_4__ {size_t length; char* data; size_t max; int flags; } ;
typedef  TYPE_1__ BUF_MEM ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_F_BUF_MEM_GROW_CLEAN ; 
 int BUF_MEM_FLAG_SECURE ; 
 int /*<<< orphan*/  BUFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 size_t LIMIT_BEFORE_EXPANSION ; 
 char* OPENSSL_clear_realloc (char*,size_t,size_t) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 char* sec_alloc_realloc (TYPE_1__*,size_t) ; 

size_t BUF_MEM_grow_clean(BUF_MEM *str, size_t len)
{
    char *ret;
    size_t n;

    if (str->length >= len) {
        if (str->data != NULL)
            memset(&str->data[len], 0, str->length - len);
        str->length = len;
        return len;
    }
    if (str->max >= len) {
        memset(&str->data[str->length], 0, len - str->length);
        str->length = len;
        return len;
    }
    /* This limit is sufficient to ensure (len+3)/3*4 < 2**31 */
    if (len > LIMIT_BEFORE_EXPANSION) {
        BUFerr(BUF_F_BUF_MEM_GROW_CLEAN, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    n = (len + 3) / 3 * 4;
    if ((str->flags & BUF_MEM_FLAG_SECURE))
        ret = sec_alloc_realloc(str, n);
    else
        ret = OPENSSL_clear_realloc(str->data, str->max, n);
    if (ret == NULL) {
        BUFerr(BUF_F_BUF_MEM_GROW_CLEAN, ERR_R_MALLOC_FAILURE);
        len = 0;
    } else {
        str->data = ret;
        str->max = n;
        memset(&str->data[str->length], 0, len - str->length);
        str->length = len;
    }
    return len;
}