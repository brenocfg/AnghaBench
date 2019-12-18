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
struct isis_lsp_header {scalar_t__* remaining_lifetime; scalar_t__* checksum; } ;

/* Variables and functions */

__attribute__((used)) static void
isis_clear_checksum_lifetime(void *header)
{
    struct isis_lsp_header *header_lsp = (struct isis_lsp_header *) header;

    header_lsp->checksum[0] = 0;
    header_lsp->checksum[1] = 0;
    header_lsp->remaining_lifetime[0] = 0;
    header_lsp->remaining_lifetime[1] = 0;
}