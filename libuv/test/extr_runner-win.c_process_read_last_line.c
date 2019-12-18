#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  stdio_out; } ;
typedef  TYPE_1__ process_info_t ;
struct TYPE_7__ {size_t Offset; } ;
typedef  TYPE_2__ OVERLAPPED ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 size_t GetFileSize (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t INVALID_FILE_SIZE ; 
 int /*<<< orphan*/  ReadFile (int /*<<< orphan*/ ,char*,size_t,size_t*,TYPE_2__*) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

int process_read_last_line(process_info_t *p,
                           char * buffer,
                           size_t buffer_len) {
  DWORD size;
  DWORD read;
  DWORD start;
  OVERLAPPED overlapped;

  ASSERT(buffer_len > 0);

  size = GetFileSize(p->stdio_out, NULL);
  if (size == INVALID_FILE_SIZE)
    return -1;

  if (size == 0) {
    buffer[0] = '\0';
    return 1;
  }

  memset(&overlapped, 0, sizeof overlapped);
  if (size >= buffer_len)
    overlapped.Offset = size - buffer_len - 1;

  if (!ReadFile(p->stdio_out, buffer, buffer_len - 1, &read, &overlapped))
    return -1;

  start = read;
  while (start-- > 0) {
    if (buffer[start] == '\n' || buffer[start] == '\r')
      break;
  }

  if (start > 0)
    memmove(buffer, buffer + start, read - start);

  buffer[read - start] = '\0';

  return 0;
}