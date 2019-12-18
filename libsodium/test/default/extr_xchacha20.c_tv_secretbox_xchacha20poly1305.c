#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {char* member_0; char* member_1; char* member_2; char* member_3; int /*<<< orphan*/  out; int /*<<< orphan*/  m; int /*<<< orphan*/  nonce; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ XChaCha20Poly1305TV ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ crypto_secretbox_xchacha20poly1305_KEYBYTES ; 
 size_t crypto_secretbox_xchacha20poly1305_MACBYTES ; 
 scalar_t__ crypto_secretbox_xchacha20poly1305_MESSAGEBYTES_MAX ; 
 scalar_t__ crypto_secretbox_xchacha20poly1305_NONCEBYTES ; 
 int /*<<< orphan*/  crypto_secretbox_xchacha20poly1305_detached (unsigned char*,unsigned char*,unsigned char*,size_t,unsigned char*,unsigned char*) ; 
 scalar_t__ crypto_secretbox_xchacha20poly1305_easy (unsigned char*,unsigned char*,size_t,unsigned char*,unsigned char*) ; 
 scalar_t__ crypto_secretbox_xchacha20poly1305_keybytes () ; 
 size_t crypto_secretbox_xchacha20poly1305_macbytes () ; 
 scalar_t__ crypto_secretbox_xchacha20poly1305_messagebytes_max () ; 
 scalar_t__ crypto_secretbox_xchacha20poly1305_noncebytes () ; 
 scalar_t__ crypto_secretbox_xchacha20poly1305_open_detached (unsigned char*,unsigned char*,unsigned char*,size_t,unsigned char*,unsigned char*) ; 
 int crypto_secretbox_xchacha20poly1305_open_easy (unsigned char*,unsigned char*,size_t,unsigned char*,unsigned char*) ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  printf (char*) ; 
 size_t randombytes_uniform (scalar_t__) ; 
 int /*<<< orphan*/  sodium_free (unsigned char*) ; 
 int /*<<< orphan*/  sodium_hex2bin (unsigned char*,size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sodium_malloc (size_t) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tv_secretbox_xchacha20poly1305(void)
{
    static const XChaCha20Poly1305TV tvs[] = {
        { "065ff46a9dddb1ab047ee5914d6d575a828b8cc1f454b24e8cd0f57efdc49a34", "f83262646ce01293b9923a65a073df78c54b2e799cd6c4e5", "", "4c72340416339dcdea01b760db5adaf7" },
        { "d3c71d54e6b13506e07aa2e7b412a17a7a1f34df3d3148cd3f45b91ccaa5f4d9", "943b454a853aa514c63cf99b1e197bbb99da24b2e2d93e47", "76bd706e07741e713d90efdb34ad202067263f984942aae8bda159f30dfccc72200f8093520b85c5ad124ff7c8b2d920946e5cfff4b819abf84c7b35a6205ca72c9f8747c3044dd73fb4bebda1b476", "0384276f1cfa5c82c3e58f0f2acc1f821c6f526d2c19557cf8bd270fcde43fba1d88890663f7b2f5c6b1d7deccf5c91b4df5865dc55cc7e04d6793fc2db8f9e3b418f95cb796d67a7f3f7e097150cb607c435dacf82eac3d669866e5092ace" },
        { "9498fdb922e0596e32af7f8108def2068f5a32a5ac70bd33ade371701f3d98d0", "a0056f24be0d20106fe750e2ee3684d4457cbdcb3a74e566", "b1bc9cfedb340fb06a37eba80439189e48aa0cfd37020eec0afa09165af12864671b3fbddbbb20ac18f586f2f66d13b3ca40c9a7e21c4513a5d87a95319f8ca3c2151e2a1b8b86a35653e77f90b9e63d2a84be9b9603876a89d60fd708edcd64b41be1064b8ad1046553aaeb51dc70b8112c9915d94f2a5dad1e14e7009db6c703c843a4f64b77d44b179b9579ac497dac2d33", "4918790d46893fa3dca74d8abc57eef7fca2c6393d1beef5efa845ac20475db38d1a068debf4c5dbd8614eb072877c565dc52bd40941f0b590d2079a5028e426bf50bcbaadcbebf278bddceedc578a5e31379523dee15026ec82d34e56f2871fdf13255db199ac48f163d5ee7e4f4e09a39451356959d9242a39aea33990ab960a4c25346e3d9397fc5e7cb6266c2476411cd331f2bcb4486750c746947ec6401865d5" },
        { "fa2d915e044d0519248150e7c815b01f0f2a691c626f8d22c3ef61e7f16eea47", "c946065dc8befa9cc9f292ea2cf28f0256285565051792b7", "d5be1a24c7872115dc5c5b4234dbee35a6f89ae3a91b3e33d75249a0aecfed252341295f49296f7ee14d64de1ea6355cb8facd065052d869aeb1763cda7e418a7e33b6f7a81327181df6cd4de3a126d9df1b5e8b0b1a6b281e63f2", "6d32e3571afec58b0acabb54a287118b3ed6691f56cc8ead12d735352c9a050c2ca173c78b6092f9ad4b7c21c36fb0ce18560956395bab3099c54760a743051ac6a898a0b0034b5e953340c975cf7a873c56b27e66bca2bff1dd977addefc7935bb7550753dd13d1f1a43d" },
        { "6f149c2ec27af45176030c8dd7ab0e1e488f5803f26f75045d7a56f59a587a85", "952aff2f39bc70016f04ac7fb8b55fd22764ba16b56e255d", "8fde598c4bde5786abdc6ab83fce66d59782b6ce36afe028c447ad4086a748764afa88a520e837a9d56d0b7693b0476649f24c2aa44b94615a1efc75", "9bccf07974836fa4609d32d9527d928d184d9c6c0823af2f703e0e257a162d26d3678fa15ab1c4db76ac42084d32cefca8efaf77814c199b310999e327a3e3daa2e235b175979504ede87b58" },
        { "b964b7fdf442efbcc2cd3e4cd596035bdfb05ed7d44f7fd4dce2d5614af5c8c4", "2886fbfa4b35b68f28d31df6243a4fbc56475b69e24820a4", "", "b83fbdd112bf0f7d62eff96c9faa8850" },
        { "10c0ad4054b48d7d1de1d9ab6f782ca883d886573e9d18c1d47b6ee6b5208189", "977edf57428d0e0247a3c88c9a9ec321bbaae1a4da8353b5", "518e4a27949812424b2a381c3efea6055ee5e75eff", "0c801a037c2ed0500d6ef68e8d195eceb05a15f8edb68b35773e81ac2aca18e9be53416f9a" },
        { "7db0a81d01699c86f47a3ec76d46aa32660adad7f9ac72cf8396419f789f6bb1", "e7cb57132ce954e28f4470cca1dbda20b534cdf32fbe3658", "ee6511d403539e611ab312205f0c3b8f36a33d36f1dc44bb33d6836f0ab93b9f1747167bf0150f045fcd12a39479641d8bdde6fe01475196e8fe2c435e834e30a59f6aaa01ebcd", "ae8b1d4df4f982b2702626feca07590fedd0dfa7ae34e6a098372a1aa32f9fbf0ce2a88b5c16a571ef48f3c9fda689ce8ebb9947c9e2a28e01b1191efc81ad2ce0ed6e6fc7c164b1fc7f3d50b7f5e47a895db3c1fc46c0" },
        { "7b043dd27476cf5a2baf2907541d8241ecd8b97d38d08911737e69b0846732fb", "74706a2855f946ed600e9b453c1ac372520b6a76a3c48a76", "dbf165bb8352d6823991b99f3981ba9c8153635e5695477cba54e96a2a8c4dc5f9dbe817887d7340e3f48a", "ce57261afba90a9598de15481c43f26f7b8c8cb2806c7c977752dba898dc51b92a3f1a62ebf696747bfccf72e0edda97f2ccd6d496f55aefbb3ec2" },
        { "e588e418d658df1b2b1583122e26f74ca3506b425087bea895d81021168f8164", "4f4d0ffd699268cd841ce4f603fe0cd27b8069fcf8215fbb", "f91bcdcf4d08ba8598407ba8ef661e66c59ca9d89f3c0a3542e47246c777091e4864e63e1e3911dc01257255e551527a53a34481be", "22dc88de7cacd4d9ce73359f7d6e16e74caeaa7b0d1ef2bb10fda4e79c3d5a9aa04b8b03575fd27bc970c9ed0dc80346162469e0547030ddccb8cdc95981400907c87c9442" }
    };
    const XChaCha20Poly1305TV *tv;
    unsigned char             *m;
    unsigned char             *nonce;
    unsigned char             *key;
    unsigned char             *out;
    unsigned char             *out2;
    size_t                     m_len;
    size_t                     n;
    size_t                     i;

    key = (unsigned char *) sodium_malloc
        (crypto_secretbox_xchacha20poly1305_KEYBYTES);
    nonce = (unsigned char *) sodium_malloc
        (crypto_secretbox_xchacha20poly1305_NONCEBYTES);
    for (i = 0; i < (sizeof tvs) / (sizeof tvs[0]); i++) {
        tv = &tvs[i];
        m_len = strlen(tv->m) / 2;
        m = (unsigned char *) sodium_malloc(m_len);
        sodium_hex2bin(key, crypto_secretbox_xchacha20poly1305_KEYBYTES,
                       tv->key, strlen(tv->key), NULL, NULL, NULL);
        sodium_hex2bin(nonce, crypto_secretbox_xchacha20poly1305_NONCEBYTES,
                       tv->nonce, strlen(tv->nonce), NULL, NULL, NULL);
        sodium_hex2bin(m, m_len, tv->m, strlen(tv->m), NULL, NULL, NULL);
        out = (unsigned char *) sodium_malloc
            (crypto_secretbox_xchacha20poly1305_MACBYTES + m_len);
        out2 = (unsigned char *) sodium_malloc
            (crypto_secretbox_xchacha20poly1305_MACBYTES + m_len);
        sodium_hex2bin(out, crypto_secretbox_xchacha20poly1305_MACBYTES + m_len,
                       tv->out, strlen(tv->out), NULL, NULL, NULL);
        assert(crypto_secretbox_xchacha20poly1305_easy(out2, m, 0, nonce, key) == 0);
        assert(crypto_secretbox_xchacha20poly1305_easy(out2, m, m_len, nonce, key) == 0);
        assert(memcmp(out, out2,
                      crypto_secretbox_xchacha20poly1305_MACBYTES + m_len) == 0);
        n = randombytes_uniform(crypto_secretbox_xchacha20poly1305_MACBYTES + (uint32_t) m_len);
        assert(crypto_secretbox_xchacha20poly1305_open_easy
               (out2, out2, crypto_secretbox_xchacha20poly1305_MACBYTES - 1,
                nonce, key) == -1);
        assert(crypto_secretbox_xchacha20poly1305_open_easy
               (out2, out2, 0,
                nonce, key) == -1);
        out2[n]++;
        assert(crypto_secretbox_xchacha20poly1305_open_easy
               (out2, out2, crypto_secretbox_xchacha20poly1305_MACBYTES + m_len,
                nonce, key) == -1);
        out2[n]--;
        nonce[0]++;
        assert(crypto_secretbox_xchacha20poly1305_open_easy
               (out2, out2, crypto_secretbox_xchacha20poly1305_MACBYTES + m_len,
                nonce, key) == -1);
        nonce[0]--;
        assert(crypto_secretbox_xchacha20poly1305_open_easy
               (out2, out2, crypto_secretbox_xchacha20poly1305_MACBYTES + m_len,
                nonce, key) == 0);
        assert(crypto_secretbox_xchacha20poly1305_open_easy
               (out2, out2, crypto_secretbox_xchacha20poly1305_MACBYTES - 1,
                nonce, key) == -1);
        assert(crypto_secretbox_xchacha20poly1305_open_easy
               (out2, out2, 0, nonce, key) == -1);
        assert(memcmp(m, out2, m_len) == 0);
        assert(crypto_secretbox_xchacha20poly1305_open_detached
               (out2, out + crypto_secretbox_xchacha20poly1305_MACBYTES, out,
                m_len, nonce, key) == 0);
        assert(crypto_secretbox_xchacha20poly1305_open_detached
               (NULL, out + crypto_secretbox_xchacha20poly1305_MACBYTES, out,
                m_len, nonce, key) == 0);
        crypto_secretbox_xchacha20poly1305_detached
            (out2 + crypto_secretbox_xchacha20poly1305_MACBYTES, out2, m,
             m_len, nonce, key);
        assert(memcmp(out, out2,
                      crypto_secretbox_xchacha20poly1305_MACBYTES + m_len) == 0);
        sodium_free(out);
        sodium_free(out2);
        sodium_free(m);
    }
    sodium_free(nonce);
    sodium_free(key);

    assert(crypto_secretbox_xchacha20poly1305_keybytes() == crypto_secretbox_xchacha20poly1305_KEYBYTES);
    assert(crypto_secretbox_xchacha20poly1305_noncebytes() == crypto_secretbox_xchacha20poly1305_NONCEBYTES);
    assert(crypto_secretbox_xchacha20poly1305_macbytes() == crypto_secretbox_xchacha20poly1305_MACBYTES);
    assert(crypto_secretbox_xchacha20poly1305_messagebytes_max() == crypto_secretbox_xchacha20poly1305_MESSAGEBYTES_MAX);

    printf("tv_secretbox_xchacha20: ok\n");
}