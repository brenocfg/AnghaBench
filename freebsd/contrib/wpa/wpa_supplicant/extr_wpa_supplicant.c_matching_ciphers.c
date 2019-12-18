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
struct wpa_ssid {int group_cipher; int pairwise_cipher; } ;
struct wpa_ie_data {int group_cipher; int pairwise_cipher; int /*<<< orphan*/  has_pairwise; int /*<<< orphan*/  has_group; } ;

/* Variables and functions */
 void* wpa_default_rsn_cipher (int) ; 

__attribute__((used)) static int matching_ciphers(struct wpa_ssid *ssid, struct wpa_ie_data *ie,
			    int freq)
{
	if (!ie->has_group)
		ie->group_cipher = wpa_default_rsn_cipher(freq);
	if (!ie->has_pairwise)
		ie->pairwise_cipher = wpa_default_rsn_cipher(freq);
	return (ie->group_cipher & ssid->group_cipher) &&
		(ie->pairwise_cipher & ssid->pairwise_cipher);
}