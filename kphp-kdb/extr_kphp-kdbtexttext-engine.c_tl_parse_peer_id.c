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
 int /*<<< orphan*/  TL_ERROR_BAD_VALUE ; 
 int tl_fetch_int () ; 
 int /*<<< orphan*/  tl_fetch_set_error_format (int /*<<< orphan*/ ,char*) ; 

int tl_parse_peer_id (void) {
  int peer_id = tl_fetch_int ();
  if (!peer_id) {
    tl_fetch_set_error_format (TL_ERROR_BAD_VALUE, "Peer id must be non-zero integer");
    return -1;
  }
  return peer_id;
}