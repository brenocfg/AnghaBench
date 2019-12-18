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
typedef  int kadm5_ret_t ;

/* Variables and functions */
#define  HDB_ERR_EXISTS 129 
#define  HDB_ERR_NOENTRY 128 
 int KADM5_DUP ; 
 int KADM5_UNK_PRINC ; 

kadm5_ret_t
_kadm5_error_code(kadm5_ret_t code)
{
    switch(code){
    case HDB_ERR_EXISTS:
	return KADM5_DUP;
    case HDB_ERR_NOENTRY:
	return KADM5_UNK_PRINC;
    }
    return code;
}