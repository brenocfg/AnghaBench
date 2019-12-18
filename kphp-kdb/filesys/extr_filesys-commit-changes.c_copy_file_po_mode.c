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
struct stat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  last_po ; 
 int /*<<< orphan*/  pending_operation_copyfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,unsigned char*,int,struct stat*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pending_operation_fill (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,struct stat*) ; 
 int /*<<< orphan*/  pot_copy_attrs ; 
 int /*<<< orphan*/  transaction_file_no ; 
 int /*<<< orphan*/  transaction_id ; 

__attribute__((used)) static int copy_file_po_mode (struct stat *S, char *name, unsigned char *buf, int l, int same) {
  if (same) {
    pending_operation_fill (&last_po, pot_copy_attrs, NULL, name, S);
  } else {
    pending_operation_copyfile (transaction_id, &transaction_file_no, name, buf, l, S, &last_po, NULL);
  }
  return 0;
}