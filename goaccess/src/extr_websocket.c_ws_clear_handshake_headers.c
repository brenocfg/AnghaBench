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
typedef  int /*<<< orphan*/  WSHeaders ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ws_free_header_fields (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ws_clear_handshake_headers (WSHeaders * headers)
{
  ws_free_header_fields (headers);
  free (headers);
  headers = NULL;
}