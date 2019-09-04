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
struct st_util_save_ticket_t {char* fn; } ;
typedef  int /*<<< orphan*/  ptls_t ;
typedef  int /*<<< orphan*/  ptls_save_ticket_t ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ ptls_iovec_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int PTLS_ERROR_LIBRARY ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int util_save_ticket_cb(ptls_save_ticket_t *_self, ptls_t *tls, ptls_iovec_t src)
{
    struct st_util_save_ticket_t *self = (void *)_self;
    FILE *fp;

    if ((fp = fopen(self->fn, "wb")) == NULL) {
        fprintf(stderr, "failed to open file:%s:%s\n", self->fn, strerror(errno));
        return PTLS_ERROR_LIBRARY;
    }
    fwrite(src.base, 1, src.len, fp);
    fclose(fp);

    return 0;
}