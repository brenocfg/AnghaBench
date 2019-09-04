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
struct cluster {void* crc64_array; void* binlog_buffer; void* fptr; void* wptr; void* binlog_buffer_end; } ;

/* Variables and functions */
 int BINLOG_BUFFER_SIZE ; 
 int CRC64_ARRAY_STEP_LOG ; 
 int MAX_BINLOG_SIZE ; 
 int /*<<< orphan*/  assert (void*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  vkprintf (int,char*) ; 
 struct cluster* zmalloc0 (int) ; 

struct cluster *alloc_new_cluster (void) {
  vkprintf (2, "Allocating new cluster\n");
  struct cluster *C = zmalloc0 (sizeof (struct cluster));
  C->binlog_buffer = malloc (BINLOG_BUFFER_SIZE * 2);
  assert (C->binlog_buffer);
  C->binlog_buffer_end = C->binlog_buffer + BINLOG_BUFFER_SIZE * 2;
  C->wptr = C->binlog_buffer;
  C->fptr = C->binlog_buffer;
  C->crc64_array = malloc ((MAX_BINLOG_SIZE >> CRC64_ARRAY_STEP_LOG) * 8);
  assert (C->crc64_array);
  return C;
}