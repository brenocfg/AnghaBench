#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* key_data_contents; int /*<<< orphan*/ * key_data_length; } ;
typedef  TYPE_1__ krb5_key_data ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
kadm5_free_key_data(void *server_handle,
		    int16_t *n_key_data,
		    krb5_key_data *key_data)
{
    int i;
    for(i = 0; i < *n_key_data; i++){
	if(key_data[i].key_data_contents[0]){
	    memset(key_data[i].key_data_contents[0],
		   0,
		   key_data[i].key_data_length[0]);
	    free(key_data[i].key_data_contents[0]);
	}
	if(key_data[i].key_data_contents[1])
	    free(key_data[i].key_data_contents[1]);
    }
    *n_key_data = 0;
}