#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ len; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ ptls_iovec_t ;
struct TYPE_8__ {scalar_t__ off; int /*<<< orphan*/  base; scalar_t__ is_allocated; } ;
typedef  TYPE_2__ ptls_buffer_t ;
typedef  scalar_t__ errno_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int PTLS_ERROR_PEM_LABEL_NOT_FOUND ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fopen_s (int /*<<< orphan*/ **,char const*,char*) ; 
 int /*<<< orphan*/  ptls_buffer_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  ptls_buffer_init (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int ptls_get_pem_object (int /*<<< orphan*/ *,char const*,TYPE_2__*) ; 

int ptls_load_pem_objects(char const *pem_fname, const char *label, ptls_iovec_t *list, size_t list_max, size_t *nb_objects)
{
    FILE *F;
    int ret = 0;
    size_t count = 0;
#ifdef _WINDOWS
    errno_t err = fopen_s(&F, pem_fname, "r");
    if (err != 0) {
        ret = -1;
    }
#else
    F = fopen(pem_fname, "r");
    if (F == NULL) {
        ret = -1;
    }
#endif

    *nb_objects = 0;

    if (ret == 0) {
        while (count < list_max) {
            ptls_buffer_t buf;

            ptls_buffer_init(&buf, "", 0);

            ret = ptls_get_pem_object(F, label, &buf);

            if (ret == 0) {
                if (buf.off > 0 && buf.is_allocated) {
                    list[count].base = buf.base;
                    list[count].len = buf.off;
                    count++;
                } else {
                    ptls_buffer_dispose(&buf);
                }
            } else {
                ptls_buffer_dispose(&buf);
                break;
            }
        }
    }

    if (ret == PTLS_ERROR_PEM_LABEL_NOT_FOUND && count > 0) {
        ret = 0;
    }

    *nb_objects = count;

    if (F != NULL) {
        fclose(F);
    }

    return ret;
}