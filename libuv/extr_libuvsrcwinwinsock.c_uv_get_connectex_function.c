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
typedef  int /*<<< orphan*/  SOCKET ;
typedef  int /*<<< orphan*/  LPFN_CONNECTEX ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  WSAID_CONNECTEX ; 
 int /*<<< orphan*/  uv_get_extension_function (int /*<<< orphan*/ ,int /*<<< orphan*/  const,void**) ; 

BOOL uv_get_connectex_function(SOCKET socket, LPFN_CONNECTEX* target) {
  const GUID wsaid_connectex = WSAID_CONNECTEX;
  return uv_get_extension_function(socket, wsaid_connectex, (void**)target);
}