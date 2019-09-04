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
typedef  int /*<<< orphan*/  ptls_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 scalar_t__ ptls_load_certificates (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void load_certificate_chain(ptls_context_t *ctx, const char *fn)
{
    if (ptls_load_certificates(ctx, (char *)fn) != 0) {
        fprintf(stderr, "failed to load certificate:%s:%s\n", fn, strerror(errno));
        exit(1);
    }
}