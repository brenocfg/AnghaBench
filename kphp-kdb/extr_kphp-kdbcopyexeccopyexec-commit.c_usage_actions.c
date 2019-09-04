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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void usage_actions (void) {
  fprintf (stderr,
    "Mandatory actions commands:\n"
    "\tkey <key-id>\tset private key-id for transaction encryption.\n"
    "\tmask <mask>\tset transaction mask.\n"
    "Other actions commands:\n"
    "\twaiting\tset waiting flag to the transaction (transaction will wait till previously running transactions ends).\n"
    "\trerun\tset rerun flag (transaction will be rerun in the case of interrupted status).\n"
    "\timportant\tset important flag to the transaction.\n"
    "\tcp <src-filename> [dst-filename]\tcopy filename to temporary transaction directory, if dst-filename isn't given then it will equal to the <src-filename> basename.\n"
    "\t\tin case <src-filename> doesn't contain any slash copyexec-commit copies file from transaction-dir,\n"
    "\t\totherwise copyexec-commit considers <src-filename> as absolute path\n"
    "\t\tin the case when <src-filename> contains blanks, it is possible to enclose it into double quotes.\n"
    "\texec <cmd>\texecute \"/bin/sh -c cmd\" in child process and wait till this command terminates.\n"
    "\texec_check <cmd>\texecute <cmd> and terminate transaction if command returns not zero exit code or was killed by signal.\n"
    "\texec_result <cmd>\texecute <cmd> and set transaction's result by status obtained from waitpid call\n"
    "\twait <transaction_id>\twait till given transaction terminates\n"
    "\tkill <signal> <transaction_id>\tsend signal (2 or 15) to given transaction and wait till it terminates.\n"
    "\tcancel <transaction_id>\tsend signal SIGUSR2 to <transaction_id>, if no command in <transaction_id> hadn't executed, it will be cancelled.\n"
    "\tresult <int>\tset transaction's result by given <int>\n"
    "Inserting synchronization point (example: new apache server)\n"
    "\tsynchronize \"actions\" file should contain only 3 lines with key, mask and synchronize\n"
    );
}