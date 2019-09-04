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
struct lev_cache_uri {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_uri_f (char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cache_uri_add (struct lev_cache_uri *E, int l) {
  char uri[256];
  memcpy (uri, E->data, l);
  uri[l] = 0;
  get_uri_f (uri, 1);
}