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
 int /*<<< orphan*/  dtoa_ctx_key ; 
 struct dtoa_context* pthread_getspecific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_setspecific (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_dtoa_ctx_dtor (struct dtoa_context*) ; 

__attribute__((used)) static void tsd_dtoa_ctx_fini() {
  struct dtoa_context *ctx = pthread_getspecific(dtoa_ctx_key);
  tsd_dtoa_ctx_dtor(ctx);
  pthread_setspecific(dtoa_ctx_key, NULL);
}