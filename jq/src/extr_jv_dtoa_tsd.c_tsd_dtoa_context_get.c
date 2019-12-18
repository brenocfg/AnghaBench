#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dtoa_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  dtoa_ctx_key ; 
 int /*<<< orphan*/  dtoa_ctx_once ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jvp_dtoa_context_init (struct dtoa_context*) ; 
 struct dtoa_context* malloc (int) ; 
 scalar_t__ pthread_getspecific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_setspecific (int /*<<< orphan*/ ,struct dtoa_context*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tsd_dtoa_ctx_init ; 

inline struct dtoa_context *tsd_dtoa_context_get() {
  pthread_once(&dtoa_ctx_once, tsd_dtoa_ctx_init); // cannot fail
  struct dtoa_context *ctx = (struct dtoa_context*)pthread_getspecific(dtoa_ctx_key);
  if (!ctx) {
    ctx = malloc(sizeof(struct dtoa_context));
    jvp_dtoa_context_init(ctx);
    if (pthread_setspecific(dtoa_ctx_key, ctx) != 0) {
      fprintf(stderr, "error: cannot set thread specific data");
      abort();
    }
  }
  return ctx;
}