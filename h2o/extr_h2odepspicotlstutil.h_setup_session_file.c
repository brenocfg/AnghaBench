#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ticket ;
struct TYPE_8__ {int /*<<< orphan*/  cb; } ;
struct st_util_save_ticket_t {TYPE_2__ super; int /*<<< orphan*/  fn; } ;
struct TYPE_7__ {int /*<<< orphan*/  session_ticket; } ;
struct TYPE_9__ {TYPE_1__ client; } ;
typedef  TYPE_3__ ptls_handshake_properties_t ;
struct TYPE_10__ {TYPE_2__* save_ticket; } ;
typedef  TYPE_4__ ptls_context_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 size_t fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptls_iovec_init (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  util_save_ticket_cb ; 

__attribute__((used)) static inline void setup_session_file(ptls_context_t *ctx, ptls_handshake_properties_t *hsprop, const char *fn)
{
    static struct st_util_save_ticket_t st;
    FILE *fp;

    /* setup save_ticket callback */
    strcpy(st.fn, fn);
    st.super.cb = util_save_ticket_cb;
    ctx->save_ticket = &st.super;

    /* load session ticket if possible */
    if ((fp = fopen(fn, "rb")) != NULL) {
        static uint8_t ticket[16384];
        size_t ticket_size = fread(ticket, 1, sizeof(ticket), fp);
        if (ticket_size == 0 || !feof(fp)) {
            fprintf(stderr, "failed to load ticket from file:%s\n", fn);
            exit(1);
        }
        fclose(fp);
        hsprop->client.session_ticket = ptls_iovec_init(ticket, ticket_size);
    }
}