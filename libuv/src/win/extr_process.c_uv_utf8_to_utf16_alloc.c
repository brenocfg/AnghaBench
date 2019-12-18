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
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int ERROR_OUTOFMEMORY ; 
 int GetLastError () ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ uv__malloc (int) ; 

__attribute__((used)) static int uv_utf8_to_utf16_alloc(const char* s, WCHAR** ws_ptr) {
  int ws_len, r;
  WCHAR* ws;

  ws_len = MultiByteToWideChar(CP_UTF8,
                               0,
                               s,
                               -1,
                               NULL,
                               0);
  if (ws_len <= 0) {
    return GetLastError();
  }

  ws = (WCHAR*) uv__malloc(ws_len * sizeof(WCHAR));
  if (ws == NULL) {
    return ERROR_OUTOFMEMORY;
  }

  r = MultiByteToWideChar(CP_UTF8,
                          0,
                          s,
                          -1,
                          ws,
                          ws_len);
  assert(r == ws_len);

  *ws_ptr = ws;
  return 0;
}