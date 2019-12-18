__attribute__((used)) static int test_ecb(void)
{
#ifdef EAP_PSK
	struct ecb_test_vector {
		char *key;
		char *plaintext;
		char *ciphertext;
	} vectors[] = {
		/* CAVS 11.1 - ECBGFSbox128.rsp */
		{
			"00000000000000000000000000000000",
			"f34481ec3cc627bacd5dc3fb08f273e6",
			"0336763e966d92595a567cc9ce537f5e"
		},
		{
			"00000000000000000000000000000000",
			"9798c4640bad75c7c3227db910174e72",
			"a9a1631bf4996954ebc093957b234589"
		},
		{
			"00000000000000000000000000000000",
			"96ab5c2ff612d9dfaae8c31f30c42168",
			"ff4f8391a6a40ca5b25d23bedd44a597"
		},
		{
			"00000000000000000000000000000000",
			"6a118a874519e64e9963798a503f1d35",
			"dc43be40be0e53712f7e2bf5ca707209"
		},
		{
			"00000000000000000000000000000000",
			"cb9fceec81286ca3e989bd979b0cb284",
			"92beedab1895a94faa69b632e5cc47ce"
		},
		{
			"00000000000000000000000000000000",
			"b26aeb1874e47ca8358ff22378f09144",
			"459264f4798f6a78bacb89c15ed3d601"
		},
		{
			"00000000000000000000000000000000",
			"58c8e00b2631686d54eab84b91f0aca1",
			"08a4e2efec8a8e3312ca7460b9040bbf"
		},
		/* CAVS 11.1 - ECBKeySbox128.rsp */
		{
			"10a58869d74be5a374cf867cfb473859",
			"00000000000000000000000000000000",
			"6d251e6944b051e04eaa6fb4dbf78465"
		},
		{
			"caea65cdbb75e9169ecd22ebe6e54675",
			"00000000000000000000000000000000",
			"6e29201190152df4ee058139def610bb",
		}
	};
	int ret = 0;
	unsigned int i;
	u8 key[16], plain[16], cipher[16], out[16];

	for (i = 0; i < ARRAY_SIZE(vectors); i++) {
		struct ecb_test_vector *tv = &vectors[i];

		if (hexstr2bin(tv->key, key, sizeof(key)) ||
		    hexstr2bin(tv->plaintext, plain, sizeof(plain)) ||
		    hexstr2bin(tv->ciphertext, cipher, sizeof(cipher))) {
			wpa_printf(MSG_ERROR, "Invalid AES-ECB test vector %u",
				   i);
			ret++;
			continue;
		}

		if (aes_128_encrypt_block(key, plain, out) < 0 ||
		    os_memcmp(out, cipher, 16) != 0) {
			wpa_printf(MSG_ERROR, "AES-ECB encrypt %u failed", i);
			ret++;
		}
	}

	if (!ret)
		wpa_printf(MSG_INFO, "AES ECB mode test cases passed");

	return ret;
#endif /* EAP_PSK */

	return 0;
}