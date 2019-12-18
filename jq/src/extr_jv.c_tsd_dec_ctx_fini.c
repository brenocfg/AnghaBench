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

/* Variables and functions */
 int /*<<< orphan*/  dec_ctx_dbl_key ; 
 int /*<<< orphan*/  dec_ctx_key ; 
 int /*<<< orphan*/  jv_mem_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_getspecific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_setspecific (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tsd_dec_ctx_fini() {
  jv_mem_free(pthread_getspecific(dec_ctx_key));
  jv_mem_free(pthread_getspecific(dec_ctx_dbl_key));
  pthread_setspecific(dec_ctx_key, NULL);
  pthread_setspecific(dec_ctx_dbl_key, NULL);
}