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
struct sync_state {int /*<<< orphan*/  last_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  scalloc (size_t,int) ; 

__attribute__((used)) static int _sync_json_key(void *extra, const unsigned char *val, size_t len) {
    struct sync_state *state = extra;
    FREE(state->last_key);
    state->last_key = scalloc(len + 1, 1);
    memcpy(state->last_key, val, len);
    return 1;
}